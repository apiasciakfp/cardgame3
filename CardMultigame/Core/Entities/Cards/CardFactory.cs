using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Core.Entities.Cards
{
    public class CardFactory
    {
        public virtual List<Card> CreateCollection(string cardStrings)
        {
            string cardPrototypePattern = @"((\b\w{2,3}\b)+)";

            Regex regexObj = new Regex(cardPrototypePattern, RegexOptions.Multiline);
            MatchCollection cardPrototypes = regexObj.Matches(cardStrings);

            List<Card> cards = new List<Card>();
            foreach (Match cardPrototypeMatch in cardPrototypes)
            {
                string prototype = cardPrototypeMatch.Value;
                if (this.IsValidCardPrototype(prototype))
                {
                    cards.Add(this.CreateSingle(prototype));
                }
            }

            return cards;
        }

        public virtual Card CreateSingle(string prototype)
        {
            if(IsValidCardPrototype(prototype) == false)
            {
                return this.DamagedCard();
            }

            string rank = this.ExtractRank(prototype);
            string colour = this.ExtractColour(prototype);

            return new Card(rank, colour);
        }


        private string ExtractColour(string prototype)
        {
            string colourSign = prototype.Substring(prototype.Length - 1);

            if (colourSign.ToUpper() == "S") return "S";
            if (colourSign.ToUpper() == "H") return "H";
            if (colourSign.ToUpper() == "D") return "D";
            if (colourSign.ToUpper() == "C") return "C";

            throw new ArgumentException("Colour extraction failed. Instead of SHDC we got: " + colourSign);
        }

        private string ExtractRank(string prototype)
        {
            string rankSign = prototype.Substring(0, prototype.Length - 1);
            return rankSign;
        }

        private Card DamagedCard()
        {
            return new Card("Damaged", "Damaged");
        }

        private bool IsValidCardPrototype(string prototype)
        {
            string exactCardPrototypePattern = @"\b(10[shdcSHDC]|[2-9jqkaJQKA][shdcSHDC])\b";
            Regex regexObj = new Regex(exactCardPrototypePattern, RegexOptions.Multiline);
            Match cardPrototypes = regexObj.Match(prototype);

            if(cardPrototypes.Value != string.Empty)
            {
                return true;
            }

            return false;
        }
    }
}
