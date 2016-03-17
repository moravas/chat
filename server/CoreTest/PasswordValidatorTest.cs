using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

using Core;

namespace CoreTest
{
    [TestClass]
    public class PasswordValidatorTest
    {
        [TestInitialize]
        public void SetUp()
        {
            _validator = new PasswordValidator() { MinLenght = 8, Statements = new List<ValidatorStatement>() };
            _validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = new HashSet<char>("0123456789") });
            _validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = new HashSet<char>("ABCDEFGHIJKLMNOPQRSTUVWXYZ") });
            _validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = new HashSet<char>("abcdefghijklmnopqrstuvwxyz") });
        }

        [TestCleanup]
        public void TearDown()
        {
        }

        [TestMethod]
        public void ValidPwd()
        {
            Assert.IsTrue(_validator.Validate("ValibBob01"));
            Assert.IsTrue(_validator.Validate("VALIDbBob01"));
            Assert.IsTrue(_validator.Validate("ValibBob01235658486"));
            Assert.IsTrue(_validator.Validate("Valib.Bob@01"));
            Assert.IsTrue(_validator.Validate("_+!VBob01"));
        }

        [TestMethod]
        public void InvalidPwd()
        {
            Assert.IsFalse(_validator.Validate("v"));
            Assert.IsFalse(_validator.Validate("VAlibBobob"));
            Assert.IsFalse(_validator.Validate("VAlibBobob1"));
            Assert.IsFalse(_validator.Validate("12345678a"));
            Assert.IsFalse(_validator.Validate("12345678A"));
            Assert.IsFalse(_validator.Validate("*-/+@__A1"));
            Assert.IsFalse(_validator.Validate("*-/+@__ABb1"));
        }

        PasswordValidator _validator;
    }
}
