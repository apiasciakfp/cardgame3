using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Technical.Parsers.ParseStrategies
{
    public class SemicolonParseStrategy : IParseStrategy
    {
        private string _separator = ";";

        public string Separator()
        {
            return _separator;
        }

        public List<string> SplitIntoRecords(string orderString)
        {
            var records = orderString.Split(new[] { _separator }, StringSplitOptions.None);

            List<string> sanitizedRecords = new List<string>();
            foreach(string record in records)
            {
                if(string.IsNullOrEmpty(record) == false)
                {
                    var sanitized = record.Trim();
                    if (string.IsNullOrEmpty(record) == false)
                    {
                        sanitizedRecords.Add(record);
                    }
                }
            }

            return sanitizedRecords;
        }
    }
}
