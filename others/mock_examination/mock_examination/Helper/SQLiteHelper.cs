using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SQLite;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace mock_examination.Helper
{
	public class SQLiteHelper
	{
		private static string connectionString = string.Empty;

		/// <summary>
		/// 根据数据源、密码、版本号设置连接字符串。
		/// </summary>
		/// <param name="datasource">数据源。</param>
		/// <param name="password">密码。</param>
		/// <param name="version">版本号（缺省为3）。</param>
		public static void SetConnectionString(string datasource, int version = 3)
		{
			connectionString = string.Format("Data Source={0};Version={1};",
				datasource, version);
		}

		/// <summary>
		/// 创建一个数据库文件。如果存在同名数据库文件，则会覆盖。
		/// </summary>
		/// <param name="dbName">数据库文件名。为null或空串时不创建。</param>
		/// <param name="password">（可选）数据库密码，默认为空。</param>
		/// <exception cref="Exception"></exception>
		public static void CreateDB(string dbName)
		{
			if (!string.IsNullOrEmpty(dbName))
			{
				try { SQLiteConnection.CreateFile(dbName); }
				catch (Exception) { throw; }
			}
		}

		/// <summary> 
		/// 对SQLite数据库执行增删改操作，返回受影响的行数。 
		/// </summary> 
		/// <param name="sql">要执行的增删改的SQL语句。</param> 
		/// <param name="parameters">执行增删改语句所需要的参数，参数必须以它们在SQL语句中的顺序为准。</param> 
		/// <returns></returns> 
		/// <exception cref="Exception"></exception>
		public static int ExecuteNonQuery(string sql, params SQLiteParameter[] parameters)
		{
			int affectedRows = 0;
			using (SQLiteConnection connection = new SQLiteConnection(connectionString))
			{
				using (SQLiteCommand command = new SQLiteCommand(connection))
				{
					try
					{
						connection.Open();
						command.CommandText = sql;
						if (parameters.Length != 0)
						{
							command.Parameters.AddRange(parameters);
						}
						affectedRows = command.ExecuteNonQuery();
					}
					catch (Exception) { throw; }
				}
			}
			return affectedRows;
		}
		public static int ExecuteNonQuery(string sql)
		{
			int affectedRows = 0;
			using (SQLiteConnection connection = new SQLiteConnection(connectionString))
			{
				using (SQLiteCommand command = new SQLiteCommand(connection))
				{
					try
					{
						connection.Open();
						command.CommandText = sql;
						affectedRows = command.ExecuteNonQuery();
					}
					catch (Exception) { throw; }
				}
			}
			return affectedRows;
		}

		/// <summary>
		/// 批量处理数据操作语句。
		/// </summary>
		/// <param name="list">SQL语句集合。</param>
		/// <exception cref="Exception"></exception>
		public static void ExecuteNonQueryBatch(List<KeyValuePair<string, SQLiteParameter[]>> list)
		{
			using (SQLiteConnection conn = new SQLiteConnection(connectionString))
			{
				try { conn.Open(); }
				catch { throw; }
				using (SQLiteTransaction tran = conn.BeginTransaction())
				{
					using (SQLiteCommand cmd = new SQLiteCommand(conn))
					{
						try
						{
							foreach (var item in list)
							{
								cmd.CommandText = item.Key;
								if (item.Value != null)
								{
									cmd.Parameters.AddRange(item.Value);
								}
								cmd.ExecuteNonQuery();
							}
							tran.Commit();
						}
						catch (Exception) { tran.Rollback(); throw; }
					}
				}
			}
		}

		/// <summary>
		/// 执行查询语句，并返回第一个结果。
		/// </summary>
		/// <param name="sql">查询语句。</param>
		/// <returns>查询结果。</returns>
		/// <exception cref="Exception"></exception>
		public static object ExecuteScalar(string sql, params SQLiteParameter[] parameters)
		{
			using (SQLiteConnection conn = new SQLiteConnection(connectionString))
			{
				using (SQLiteCommand cmd = new SQLiteCommand(conn))
				{
					try
					{
						conn.Open();
						cmd.CommandText = sql;
						if (parameters.Length != 0)
						{
							cmd.Parameters.AddRange(parameters);
						}
						return cmd.ExecuteScalar();
					}
					catch (Exception) { throw; }
				}
			}
		}

		/// <summary> 
		/// 执行一个查询语句，返回一个包含查询结果的DataTable。 
		/// </summary> 
		/// <param name="sql">要执行的查询语句。</param> 
		/// <param name="parameters">执行SQL查询语句所需要的参数，参数必须以它们在SQL语句中的顺序为准。</param> 
		/// <returns></returns> 
		/// <exception cref="Exception"></exception>
		public static DataTable ExecuteQuery(string sql, params SQLiteParameter[] parameters)
		{
			using (SQLiteConnection connection = new SQLiteConnection(connectionString))
			{
				using (SQLiteCommand command = new SQLiteCommand(sql, connection))
				{
					if (parameters.Length != 0)
					{
						command.Parameters.AddRange(parameters);
					}
					SQLiteDataAdapter adapter = new SQLiteDataAdapter(command);
					DataTable data = new DataTable();
					try { adapter.Fill(data); }
					catch (Exception) { throw; }
					return data;
				}
			}
		}
		public static DataTable ExecuteQuery(string sql)
		{
			using (SQLiteConnection connection = new SQLiteConnection(connectionString))
			{
				using (SQLiteCommand command = new SQLiteCommand(sql, connection))
				{
					SQLiteDataAdapter adapter = new SQLiteDataAdapter(command);
					DataTable data = new DataTable();
					try { adapter.Fill(data); }
					catch (Exception) { throw; }
					return data;
				}
			}
		}

		/// <summary> 
		/// 执行一个查询语句，返回一个关联的SQLiteDataReader实例。 
		/// </summary> 
		/// <param name="sql">要执行的查询语句。</param> 
		/// <param name="parameters">执行SQL查询语句所需要的参数，参数必须以它们在SQL语句中的顺序为准。</param> 
		/// <returns></returns> 
		/// <exception cref="Exception"></exception>
		public static SQLiteDataReader ExecuteReader(string sql, params SQLiteParameter[] parameters)
		{
			SQLiteConnection connection = new SQLiteConnection(connectionString);
			SQLiteCommand command = new SQLiteCommand(sql, connection);
			try
			{
				if (parameters.Length != 0)
				{
					command.Parameters.AddRange(parameters);
				}
				connection.Open();
				return command.ExecuteReader(CommandBehavior.CloseConnection);
			}
			catch (Exception) { throw; }
		}

		/// <summary> 
		/// 查询数据库中的所有数据类型信息。
		/// </summary> 
		/// <returns></returns> 
		/// <exception cref="Exception"></exception>
		public static DataTable GetSchema()
		{
			using (SQLiteConnection connection = new SQLiteConnection(connectionString))
			{
				try
				{
					connection.Open();
					return connection.GetSchema("TABLES");
				}
				catch (Exception) { throw; }
			}
		}
	}
}
