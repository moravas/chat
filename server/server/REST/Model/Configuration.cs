using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;

namespace Server
{
    public class ConfigurationsDB : DbContext
    {
        public ConfigurationsDB() : base("PsqlConnection") { }

        public DbSet<Configuration> Configurations { get; set; }
    }

    [Table("configurations", Schema = "public")]
    public class Configuration
    {
        [Key]
        [Column("id")]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public long ID { get; set; }

        [Required]
        [Column("key")]
        public string Key { get; set; }

        [Required]
        [Column("value")]
        public byte[] Value { get; set; }

        [ForeignKey("UserID")]
        public virtual User User { get; set; }

        [Column("userid")]
        public int UserID { get; set; }
    }
}
