using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace mock_examination.Helper
{
    public class Common
    {
        public static string Object2Json(Object _arr)
        {
            return JsonConvert.SerializeObject(_arr);
        }
        public static List<string> Json2Array(string _str)
        {
            return ((JArray)JsonConvert.DeserializeObject(_str)).ToObject<List<string>>();
        }
        public static Dictionary<string, string> Json2Dictionary(string _str)
        {
            return JsonConvert.DeserializeObject<Dictionary<string, string>>(_str);
        }
    }
}
