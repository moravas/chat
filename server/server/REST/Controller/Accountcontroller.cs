﻿using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Security.Cryptography;
using System.Text;
using System.Web.Http;

using Core;
using System.Linq;
using System.Data.Entity.Infrastructure;

namespace Server
{
    [RoutePrefix("users")]
    public class AccountController : ApiController
    {
        public AccountController(): base()
        {
            _db = new UsersDB();
            _db.Database.CreateIfNotExists();
            _validator = new PasswordValidator() { MinLenght = 8, Statements = new List<ValidatorStatement>() };
            _validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = new HashSet<char>("0123456789") });
            _validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = new HashSet<char>("ABCDEFGHIJKLMNOPQRSTUVWXYZ") });
            _validator.Statements.Add(new ValidatorStatement { ExpectedAtLeast = 2, Data = new HashSet<char>("abcdefghijklmnopqrstuvwxyz") });
        }

        [Route("{username}")]
        [HttpDelete]
        public string Delete(string username)
        {
            throw new NotImplementedException();
        }

        [Route("login")]
        [HttpPost]
        public string LogIn(User user)
        {
            throw new NotImplementedException();
        }

        [Route("logout/{username}")]
        [HttpGet]
        public string LogOut(string username)
        {
            throw new NotImplementedException();
        }

        [Route("register")]
        [HttpPost]
        public HttpResponseMessage Register(User user)
        {
            if (!_validator.Validate(user.Password))
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest);
            }

            using (SHA512 sha = new SHA512Managed())
            {
                user.Password = BitConverter.ToString(sha.ComputeHash(Encoding.UTF8.GetBytes(user.Password))).Replace("-", string.Empty);
            }

            _db.Users.Add(user);
            if(_db.GetValidationErrors().Any())
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest);
            }

            try
            {
                _db.SaveChanges();
            }
            catch (DbUpdateException)
            {
                return Request.CreateResponse(HttpStatusCode.Conflict);
            }

            return Request.CreateResponse(HttpStatusCode.Created);
        }

        private UsersDB             _db;
        private PasswordValidator   _validator;
    }
}
