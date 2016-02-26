using System;
using System.ComponentModel.DataAnnotations;

namespace Server
{
    public class User
    {
        [Key]
        public uint ID { get; set; }

        [StringLength(256, ErrorMessage = "Username length exceds the maximum.")]
        public string Username { get; set; }

        [StringLength(256, ErrorMessage = "Email length exceds the maximum.")]
        public string Email { get; set; }

        [StringLength(128, ErrorMessage = "Password length exceds the maximum.")]
        public string Password { get; set; }
        public DateTime Logoff { get; set; }
    }
}
