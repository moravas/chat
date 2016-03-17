using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Net;

using Server;

namespace ServerTest
{
    [TestClass]
    class AccountControllerTest
    {
        [TestInitialize]
        public void SetUp()
        {
            _controller = new AccountController();
        }

        [TestCleanup]
        public void TearDown()
        {
        }

        [TestMethod]
        public void InsertValidUser()
        {
            Assert.AreEqual(HttpStatusCode.Created, _controller.Register(GetPreparedUser()));
            Assert.AreEqual(HttpStatusCode.BadRequest, _controller.Register(GetPreparedUser()));
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
