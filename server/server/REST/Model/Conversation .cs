using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;

namespace Server
{
    public class ConversationsDB : DbContext
    {
        public ConversationsDB() : base("PsqlConnection") { }

        public DbSet<Conversation> Conversations { get; set; }
    }

    [Table("conversations", Schema = "public")]
    public class Conversation
    {
        [Key]
        [Column("id")]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public long ID { get; set; }

        [Required]
        [Column("time")]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public DateTime Time { get; set; }

        [Required]
        [Column("message")]
        public string Message { get; set; }

        [ForeignKey("SenderID")]
        public virtual User User { get; set; }

        [Column("senderid")]
        public int SenderID { get; set; }
    }
}
