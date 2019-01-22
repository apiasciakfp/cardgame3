using System.Collections.Generic;

namespace Core.Entities.GameStates
{
    /// <summary>
    /// This is for readability ONLY. An example implementation of 
    /// EncapsulatedContext pattern is a Dictionary of this type
    /// passed where needed.
    /// 
    /// Do not do this in the real world systems unless you REALLY know
    /// what you are doing.
    /// </summary>
    public class GameState : Dictionary<string, object>
    {

        /// <summary>
        /// This is done ONLY to make it much easier to work with for people
        /// less accustomed to working with C# Dictionaries. In normal real world stuff do not do this.
        /// </summary>
        public new object this[string index]
        {
            get
            {
                if(base.ContainsKey(index))
                    return base[index];
                else
                    return null;
            }

            set
            {
                base[index] = value;
            }
        }

    }
}
