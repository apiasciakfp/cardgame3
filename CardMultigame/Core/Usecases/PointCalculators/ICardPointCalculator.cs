using Core.Entities.Cards;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core.Usecases.PointCalculators
{
    public interface ICardPointCalculator
    {
        int CalculatePoints(Card actuallyDrawnCard);
    }
}
