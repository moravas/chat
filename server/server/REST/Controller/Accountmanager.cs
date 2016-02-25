using System;
using System.Linq;
using System.Web.Http;

namespace server
{
    [Route("users")]
    class AccountManager : ApiController
    {
        [Route("")]
        [HttpDelete]
        public void DeleteUserAccount()
        {
            string headerValues = Request.Headers.GetValues("MyCustomID").FirstOrDefault();
            Console.WriteLine(headerValues);
        }

        [Route("")]
        [HttpGet]
        public void Login()
        {
            Console.WriteLine(Request.Content);
        }

        [Route("/register")]
        [HttpPost]
        public void Register()
        {
            Console.WriteLine(Request.Content);
        }
    }
}
