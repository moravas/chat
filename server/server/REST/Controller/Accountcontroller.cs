using System;
using System.Net;
using System.Net.Http;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Web.Http;

namespace Server
{
    [RoutePrefix("users")]
    public class AccountController : ApiController
    {
        [Route("{username}")]
        [HttpDelete]
        public string DeleteUserAccount(string username)
        {
            Console.WriteLine(username);
            return "DeleteUserAccount";
        }

        [Route("login")]
        [HttpGet]
        public string GetLogin([FromBody] string credentials)
        {
            Console.WriteLine(credentials);
            return "Login";
        }

        [Route("register")]
        [HttpPost]
        public HttpResponseMessage Register(User user)
        {
            if(!IsValidPasswodForm(user.Password))
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest);
            }

            using (SHA512 sha = new SHA512Managed())
            {
                user.Password = BitConverter.ToString(sha.ComputeHash(Encoding.UTF8.GetBytes(user.Password))).Replace("-", string.Empty);
            }

            return Request.CreateResponse(HttpStatusCode.Created);
        }

        private bool IsValidPasswodForm(string password)
        {
            if(password.Length < 8 && password.Length > 256)
            {
                return false;
            }

            //^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&])[A-Za-z\d$@$!%*?&]{8,10}
            Regex LowerCaseValidator = new Regex(@"[a-z]{1}");
            Regex UpperCaseValidator = new Regex(@"[A-Z]{1}");
            Regex NumberValidator = new Regex(@"[0-9]{1}");

            int Number = 0;
            int LowerCase = 0;
            int UpperCase = 0;
            foreach(char c in password)
            {
                if(LowerCaseValidator.IsMatch(c.ToString()))
                {
                    LowerCase++;
                }
                else if (UpperCaseValidator.IsMatch(c.ToString()))
                {
                    UpperCase++;
                }
                else if (NumberValidator.IsMatch(c.ToString()))
                {
                    Number++;
                }
            }

            return (Number > 1 && UpperCase > 1 && LowerCase > 1);
        }
    }
}
