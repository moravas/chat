using System.Collections.Generic;
using System.Linq;

namespace Core
{
    public class ValidatorStatement
    {
        public int ExpectedAtLeast { get; set; }
        public HashSet<char> Data { get; set; }
    }

    public class PasswordValidator
    {
        public int MinLenght { get; set; }
        public List<ValidatorStatement> Statements { get; set; }
        public bool Validate(IEnumerable<char> data)
        {
            foreach(var s in Statements)
            {
                if(data.Intersect(s.Data).Count() < s.ExpectedAtLeast)
                {
                    return false;
                }
            }

            return true && data.Count() >= MinLenght;
        }
    }
}
