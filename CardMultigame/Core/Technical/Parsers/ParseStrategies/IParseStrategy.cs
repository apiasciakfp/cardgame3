using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Technical.Parsers.ParseStrategies
{
    public interface IParseStrategy
    {
        string Separator();
        List<string> SplitIntoRecords(string orderString);
    }
}
