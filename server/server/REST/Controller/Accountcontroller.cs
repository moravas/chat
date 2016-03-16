using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Security.Cryptography;
using System.Text;
using System.Web.Http;

using Core;

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
            PasswordValidator validator = new PasswordValidator() { MinLenght = 8 , Statements = new List<ValidatorStatement>()};
            validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = "0123456789" });
            validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" });
            validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = "abcdefghijklmnopqrstuvwxyz" });
            if (!validator.Validate(user.Password))
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest);
            }

            using (SHA512 sha = new SHA512Managed())
            {
                user.Password = BitConverter.ToString(sha.ComputeHash(Encoding.UTF8.GetBytes(user.Password))).Replace("-", string.Empty);
            }

            return Request.CreateResponse(HttpStatusCode.Created);
        }
    }
}
