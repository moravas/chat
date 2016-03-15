using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;

namespace Server
{
    public class AttachmentsDB : DbContext
    {
        public AttachmentsDB() : base("PsqlConnection") { }

        public DbSet<Attachment> Attachments { get; set; }
    }

    [Table("attachments", Schema = "public")]
    public class Attachment
    {
        [Key]
        [Column("id")]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int ID { get; set; }

        [Required]
        [Column("name")]
        [MaxLength(256, ErrorMessage = "Expected attachment name is too long")]
        public string Name { get; set; }

        [Required]
        [Column("value")]
        public byte[] Value { get; set; }

        [ForeignKey("UserID")]
        public virtual User User { get; set; }

        [Column("userid")]
        public int UserID { get; set; }
    }
}
