using System;
using System.Web.Http;

namespace Server
{
    [RoutePrefix("configuration")]
    public class ConfigurationController : ApiController
    {
        [Route("{username}/{configurationKey}")]
        [HttpDelete]
        public string DeleteConfiguration(string username, string configurationKey)
        {
            Console.WriteLine(username);
            Console.WriteLine(configurationKey);
            return "DeleteConfiguration";
        }

        [Route("{username}")]
        [HttpPost]
        public string Update(string username)
        {
            Console.WriteLine(Request.Content);
            return "Updated";
        }
    }
}
