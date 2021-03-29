using NPOI.HSSF.UserModel;
using NPOI.SS.UserModel;
using NPOI.XSSF.UserModel;
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace mock_examination.Helper
{
    /// <summary>
    /// Excel文件和DataTable之间转换帮助类
    /// </summary>
    public class ExcelHelper : IDisposable
    {
        /// <summary>
        /// 把DataTable的数据写入到指定的excel文件中
        /// </summary>
        /// <param name="TargetFileNamePath">目标文件excel的路径</param>
        /// <param name="sourceData">要写入的数据</param>
        /// <param name="sheetName">excel表中的sheet的名称，可以根据情况自己起</param>
        /// <param name="IsWriteColumnName">是否写入DataTable的列名称</param>
        /// <returns>返回写入的行数</returns>
        public static int DataTableToExcel(string TargetFileNamePath, DataTable sourceData, string sheetName, bool IsWriteColumnName)
        {

            //数据验证
            if (!File.Exists(TargetFileNamePath))
            {
                //excel文件的路径不存在
                throw new ArgumentException("excel文件的路径不存在或者excel文件没有创建好");
            }
            if (sourceData == null)
            {
                throw new ArgumentException("要写入的DataTable不能为空");
            }

            if (sheetName == null && sheetName.Length == 0)
            {
                throw new ArgumentException("excel中的sheet名称不能为空或者不能为空字符串");
            }



            //根据Excel文件的后缀名创建对应的workbook
            IWorkbook workbook = null;
            if (TargetFileNamePath.IndexOf(".xlsx") > 0)
            {  //2007版本的excel
                workbook = new XSSFWorkbook();
            }
            else if (TargetFileNamePath.IndexOf(".xls") > 0) //2003版本的excel
            {
                workbook = new HSSFWorkbook();
            }
            else
            {
                return -1;    //都不匹配或者传入的文件根本就不是excel文件，直接返回
            }



            //excel表的sheet名
            ISheet sheet = workbook.CreateSheet(sheetName);
            if (sheet == null) return -1;   //无法创建sheet，则直接返回


            //写入Excel的行数
            int WriteRowCount = 0;



            //指明需要写入列名，则写入DataTable的列名,第一行写入列名
            if (IsWriteColumnName)
            {
                //sheet表创建新的一行,即第一行
                IRow ColumnNameRow = sheet.CreateRow(0); //0下标代表第一行
                //进行写入DataTable的列名
                for (int colunmNameIndex = 0; colunmNameIndex < sourceData.Columns.Count; colunmNameIndex++)
                {
                    ColumnNameRow.CreateCell(colunmNameIndex).SetCellValue(sourceData.Columns[colunmNameIndex].ColumnName);
                }
                WriteRowCount++;
            }


            //写入数据
            for (int row = 0; row < sourceData.Rows.Count; row++)
            {
                //sheet表创建新的一行
                IRow newRow = sheet.CreateRow(WriteRowCount);
                for (int column = 0; column < sourceData.Columns.Count; column++)
                {

                    newRow.CreateCell(column).SetCellValue(sourceData.Rows[row][column].ToString());

                }

                WriteRowCount++;  //写入下一行
            }


            //写入到excel中
            FileStream fs = new FileStream(TargetFileNamePath, FileMode.Open, FileAccess.Write);
            workbook.Write(fs);

            fs.Flush();
            fs.Close();

            workbook.Close();
            return WriteRowCount;
        }

        /// <summary>
        /// 从Excel中读入数据到DataTable中
        /// </summary>
        /// <param name="sourceFileNamePath">Excel文件的路径</param>
        /// <param name="sheetName">excel文件中工作表名称</param>
        /// <param name="IsHasColumnName">文件是否有列名</param>
        /// <returns>从Excel读取到数据的DataTable结果集</returns>
        public static DataTable ExcelToDataTable(string sourceFileNamePath, int sheetIndex = 0, bool IsHasColumnName = true)
        {

            if (!File.Exists(sourceFileNamePath))
            {
                throw new ArgumentException("excel文件的路径不存在或者excel文件没有创建好");
            }

            //if (sheetName == null || sheetName.Length == 0)
            //{
            //    throw new ArgumentException("工作表sheet的名称不能为空");
            //}

            //根据Excel文件的后缀名创建对应的workbook
            IWorkbook workbook = null;
            //打开文件
            FileStream fs = new FileStream(sourceFileNamePath, FileMode.Open, FileAccess.Read);
            if (sourceFileNamePath.IndexOf(".xlsx") > 0)
            {  //2007版本的excel
                workbook = new XSSFWorkbook(fs);
            }
            else if (sourceFileNamePath.IndexOf(".xls") > 0) //2003版本的excel
            {
                workbook = new HSSFWorkbook(fs);
            }
            else
            {
                return null;    //都不匹配或者传入的文件根本就不是excel文件，直接返回
            }




            //获取工作表sheet
            ISheet sheet = workbook.GetSheetAt(sheetIndex);
            //获取不到，直接返回
            if (sheet == null) return null;



            //开始读取的行号
            int StartReadRow = 0;
            DataTable targetTable = new DataTable();



            //表中有列名,则为DataTable添加列名
            if (IsHasColumnName)
            {
                //获取要读取的工作表的第一行
                IRow columnNameRow = sheet.GetRow(0);   //0代表第一行
                                                        //获取该行的列数(即该行的长度)
                int CellLength = columnNameRow.LastCellNum;

                //遍历读取
                for (int columnNameIndex = 0; columnNameIndex < CellLength; columnNameIndex++)
                {
                    //不为空，则读入
                    if (columnNameRow.GetCell(columnNameIndex) != null)
                    {
                        //获取该单元格的值
                        string cellValue = columnNameRow.GetCell(columnNameIndex).StringCellValue;
                        if (cellValue != null)
                        {
                            //为DataTable添加列名
                            targetTable.Columns.Add(new DataColumn(cellValue));
                        }
                    }
                }

                StartReadRow++;
            }



            ///开始读取sheet表中的数据

            //获取sheet文件中的行数
            int RowLength = sheet.LastRowNum;
            //遍历一行一行地读入
            for (int RowIndex = StartReadRow; RowIndex <= RowLength; RowIndex++)
            {
                //获取sheet表中对应下标的一行数据
                IRow currentRow = sheet.GetRow(RowIndex);   //RowIndex代表第RowIndex+1行

                if (currentRow == null) continue;  //表示当前行没有数据，则继续
                //获取第Row行中的列数，即Row行中的长度
                int currentColumnLength = currentRow.LastCellNum;

                //创建DataTable的数据行
                DataRow dataRow = targetTable.NewRow();
                //遍历读取数据
                for (int columnIndex = 0; columnIndex < targetTable.Columns.Count; columnIndex++)
                {
                    //没有数据的单元格默认为空
                    if (currentRow.GetCell(columnIndex) != null)
                    {
                        dataRow[columnIndex] = currentRow.GetCell(columnIndex);
                    }
                }
                //把DataTable的数据行添加到DataTable中
                targetTable.Rows.Add(dataRow);
            }


            //释放资源
            fs.Close();
            workbook.Close();

            return targetTable;
        }


        #region IDisposable 成员

        public void Dispose()
        {

        }

        #endregion
    }
}
