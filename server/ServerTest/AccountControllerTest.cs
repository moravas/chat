using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Net;

using Server;
using System.Net.Http;
using System.Web.Http;

namespace ServerTest
{
    [TestClass]
    public class AccountcontrollerTest
    {
        [TestInitialize]
        public void SetUp()
        {
            _controller = new AccountController();
            _controller.Request = new HttpRequestMessage();
            _controller.Request.SetConfiguration(new HttpConfiguration());
        }

        [TestCleanup]
        public void TearDown()
        {
            UsersDB db = new UsersDB();
            db.Database.Delete();
        }

        [TestMethod]
        public void CreateValidUser()
        {
            Assert.AreEqual(HttpStatusCode.Created, _controller.Register(GetPreparedUser()).StatusCode);
            Assert.AreEqual(HttpStatusCode.Conflict, _controller.Register(GetPreparedUser()).StatusCode);
        }

        [TestMethod]
        public void BadUserRequest()
        {
            User user = GetPreparedUser();
            user.Password = "bob123";
            Assert.AreEqual(HttpStatusCode.BadRequest, _controller.Register(user).StatusCode);
        }

        private User GetPreparedUser()
        {
            return new User()
            {
                UserName = "ValidBob",
                Email = "validbob@email.com",
                Password = "ValidBob123"
            };
        }

        private AccountController _controller;
    }
}
