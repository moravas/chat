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
