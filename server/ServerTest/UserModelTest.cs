using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using Server;

namespace ServerTest
{
    [TestClass]
    public class UserModelTest
    {
        private UsersDB db;

        [TestInitialize]
        public void SetUp()
        {
            db = new UsersDB();
            db.Users.Create();
        }

        [TestCleanup]
        public void TearDown()
        {
            db.Users.RemoveRange(db.Users);
            db.SaveChanges();
        }

        [TestMethod]
        public void InsertValidUser()
        {
            db.Users.Add(GetPreparedUser());
            db.SaveChanges();
            foreach(User user in db.Users)
            {
                Assert.AreEqual(user.UserName, "ValidBob");
                Assert.AreEqual(user.Email, "validbob@email.com");
                Assert.AreEqual(user.Password, "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567");
                Assert.AreEqual(user.Logoff, null);
            }
        }

        [TestMethod]
        public void InsertMalformedUserName()
        {
            User user = GetPreparedUser();
            user.UserName = "_ValidBob";
            db.Users.Add(user);
            Assert.IsNotNull(db.GetValidationErrors().Count());
        }

        [TestMethod]
        public void InsertShortUserName()
        {
            User user = GetPreparedUser();
            user.UserName = "Bob";
            db.Users.Add(user);
            Assert.IsNotNull(db.GetValidationErrors().Count());
        }

        [TestMethod]
        public void InsertMalformedEmail()
        {
            User user = GetPreparedUser();
            user.Email = "validbob_at_email.com";
            db.Users.Add(user);
            Assert.IsNotNull(db.GetValidationErrors().Count());
        }

        [TestMethod]
        public void InsertMalformedPassword()
        {
            User user = GetPreparedUser();
            user.Password = "somePwd";
            db.Users.Add(user);
            Assert.IsNotNull(db.GetValidationErrors().Count());
        }

        private User GetPreparedUser()
        {
            return new User()
            {
                UserName = "ValidBob",
                Email = "validbob@email.com",
                Password = "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567"
            };
        }
    }
}
