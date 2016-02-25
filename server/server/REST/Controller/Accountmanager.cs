using System;
using System.Linq;
using System.Web.Http;

namespace Server
{
    [RoutePrefix("users")]
    public class AccountController : ApiController
    {
        [Route("")]
        [HttpDelete]
        public string DeleteUserAccount()
        {
            string headerValues = Request.Headers.GetValues("MyCustomID").FirstOrDefault();
            Console.WriteLine(headerValues);
            return "DeleteUserAccount";
        }

        [Route("login")]
        [HttpGet]
        public string Login()
        {
            Console.WriteLine(Request.Content);
            return "Login";
        }

        [Route("")]
        [HttpPost]
        public string Register()
        {
            Console.WriteLine(Request.Content);
            return "Register";
        }
    }
}
