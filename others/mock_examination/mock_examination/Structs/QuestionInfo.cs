using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace mock_examination.Structs
{
    public class QuestionInfo
    {
        public int ID;
        public string Level;
        public string File;
        public string Question;
        public Dictionary<string,string> OptionDictionary;
        public List<string> AnswerArray;

        public string Others;

        public int IsDo;
        public bool IsUse;

        public string AnswersText
        {
            get 
            {
                StringBuilder res = new StringBuilder();
                for (int index = 0; index < AnswerArray.Count; index++)
                {
                    res.Append(AnswerArray[index]);
                    if(index + 1 != AnswerArray.Count)
                        res.Append(",");
                }
                return res.ToString();
            }
        }
        public string IsDoText
        {
            get
            {
                string res = string.Empty;
                switch (IsDo)
                {
                    case 0:
                        res = "未做";
                        break;
                    case 1:
                        res = "做对";
                        break;
                    case 2:
                        res = "做错";
                        break;
                    default:
                        res = "Error";
                        break;
                }
                return res;
            }
        }
        public System.Drawing.Color IsDoColor
        {
            get
            {
                System.Drawing.Color res;
                switch (IsDo)
                {
                    case 0:
                        res = System.Drawing.Color.DarkGray;
                        break;
                    case 1:
                        res = System.Drawing.Color.DarkGreen;
                        break;
                    case 2:
                        res = System.Drawing.Color.DarkRed;
                        break;
                    default:
                        res = System.Drawing.Color.White;
                        break;
                }
                return res;
            }
        }
        public string IsUseText
        {
            get
            {
                string res = string.Empty;
                switch (IsUse)
                {
                    case false:
                        res = "停用";
                        break;
                    case true:
                        res = "启用";
                        break;
                    default:
                        res = "Error";
                        break;
                }
                return res;
            }
        }

        public QuestionInfo()
        {
            OptionDictionary = new Dictionary<string, string>();
            AnswerArray = new List<string>();
            IsDo = 0;
            IsUse = false;
        }

        public bool LoadFromDB(DataRow _dr)
        {
            try
            {
                ID = Convert.ToInt32(_dr["id"].ToString());
                Level = _dr["level"].ToString();
                File = _dr["file"].ToString();
                Question = _dr["question"].ToString();
                IsDo = Convert.ToInt32(_dr["is_do"].ToString());
                IsUse = Convert.ToInt32(_dr["is_use"].ToString()) == 1 ? true : false;
                Others = _dr["others"].ToString();

                OptionDictionary = Helper.Common.Json2Dictionary(_dr["options"].ToString());
                AnswerArray.AddRange(Helper.Common.Json2Array(_dr["answers"].ToString()));

                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public bool LoadFromExcel(DataRow _dr)
        {
            try
            {
                ID = Convert.ToInt32(_dr["序号"].ToString());
                Level = _dr["等级"].ToString();
                File = _dr["文件"].ToString();
                Question = _dr["试题题目"].ToString();

                if (string.IsNullOrWhiteSpace(_dr["选项A"].ToString()) == false)
                    OptionDictionary.Add("A", _dr["选项A"].ToString());
                if (string.IsNullOrWhiteSpace(_dr["选项B"].ToString()) == false)
                    OptionDictionary.Add("B", _dr["选项B"].ToString());
                if (string.IsNullOrWhiteSpace(_dr["选项C"].ToString()) == false)
                    OptionDictionary.Add("C", _dr["选项C"].ToString());
                if (string.IsNullOrWhiteSpace(_dr["选项D"].ToString()) == false)
                    OptionDictionary.Add("D", _dr["选项D"].ToString());

                foreach (char word in _dr["答案"].ToString())
                {
                    AnswerArray.Add(word.ToString());
                }
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        public string MakeInsertSQL()
        {
            return string.Format("INSERT INTO question_info ( question, options, answers, level, file) VALUES('{0}', '{1}', '{2}', '{3}', '{4}');",
                Question,
                Helper.Common.Object2Json(OptionDictionary),
                Helper.Common.Object2Json(AnswerArray),
                Level,
                File);
        }
        public string MakeUpdateSQL()
        {
            return string.Format("UPDATE question_info SET is_do = {0}, is_use = {1}, others = '{2}' WHERE id = {3};", IsDo, IsUse, Others, ID);
        }
        public string MakeDeleteSQL()
        {
            return string.Format("DELETE FROM question_info WHERE id = {0};", ID);
        }

        public static Dictionary<int, QuestionInfo> LoadDictionaryFormDB(System.Data.DataTable _dt)
        {
            Dictionary<int, QuestionInfo> dic = new Dictionary<int, QuestionInfo>();
            foreach (System.Data.DataRow dr in _dt.Rows)
            {
                Structs.QuestionInfo info = new Structs.QuestionInfo();
                if (true == info.LoadFromDB(dr))
                {
                    dic.Add(info.ID,info);
                }
            }
            return dic;
        }
    }
}
