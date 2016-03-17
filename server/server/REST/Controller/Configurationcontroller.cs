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
            throw new NotImplementedException();
        }

        [Route("{username}")]
        [HttpPost]
        public string Update(string username)
        {
            throw new NotImplementedException();
        }
    }
}
