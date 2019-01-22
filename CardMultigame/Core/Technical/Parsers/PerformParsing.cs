using Core.Technical.Parsers.ParseStrategies;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Core.Technical.Parsers
{
    public class PerformParsing
    {
        private IParseStrategy _parseStrategy;

        public PerformParsing(IParseStrategy parseStrategy)
        {
            this._parseStrategy = parseStrategy;
        }

        public List<Tuple<string, string>> ExecuteOn(string orderString)
        {

            List<string> records = _parseStrategy.SplitIntoRecords(orderString);

            string singleFirstWord = @"(\b\w+\b){1}";

            List<Tuple<string, string>> actionsWithParams = new List<Tuple<string, string>>();
            foreach (string record in records)
            {
                Regex regexObj = new Regex(singleFirstWord, RegexOptions.Multiline);
                Match actionSigilMatch = regexObj.Match(record);

                string actionSigil = actionSigilMatch.Value;
                string paramsSigil = record.Substring(actionSigil.Length +1);

                actionsWithParams.Add(new Tuple<string, string>(actionSigil.Trim(), paramsSigil.Trim()));
            }

            return actionsWithParams;
        }
    }
}
