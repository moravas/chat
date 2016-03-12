using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Server
{
    public class User
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public uint ID { get; set; }

        [RegularExpression(@"^[a-zA-Z0-9]{1}[a-zA-Z0-9_.]{5,255}$", ErrorMessage = "Invalid username")]
        public string UserName { get; set; }

        [DataType(DataType.EmailAddress)]
        public string Email { get; set; }

        [Range(128, 128, ErrorMessage = "Invalid password length")]
        public string Password { get; set; }

        public DateTime Logoff { get; set; }
    }
}
