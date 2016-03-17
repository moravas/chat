using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;

namespace Server
{
    public class UsersDB : DbContext
    {
        public UsersDB() : base("PsqlConnection") {}

        public DbSet<User> Users { get; set; }
    }

    [Table("users", Schema = "public")]
    public class User
    {
        [Key]
        [Column("id")]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int ID { get; set; }

        [Column("username")]
        [RegularExpression(@"^[a-zA-Z0-9]{1}[a-zA-Z0-9_.]{5,255}$", ErrorMessage = "Invalid username")]
        public string UserName { get; set; }

        [Column("email")]
        [EmailAddress]
        public string Email { get; set; }

        [Column("password")]
        [MinLength(128, ErrorMessage = "Password length is too short")]
        [MaxLength(128, ErrorMessage = "Password length is too long")]
        public string Password { get; set; }

        [Column("logoff")]
        public Nullable<DateTime> Logoff { get; set; }
    }
}
