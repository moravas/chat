using System;
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
        public string Register([FromBody] string credentials)
        {
            Console.WriteLine(credentials);
            return "Register";
        }
    }
}
