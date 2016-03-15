using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;

namespace Server
{
    public class MessageUserSwitchesDB : DbContext
    {
        public MessageUserSwitchesDB() : base("PsqlConnection") { }

        public DbSet<MessageUserSwitch> MessageUserSwitches { get; set; }
    }

    [Table("message_user_switch", Schema = "public")]
    public class MessageUserSwitch
    {
        [ForeignKey("ConversationID")]
        public virtual Conversation Conversation { get; set; }
        public long ConversationID { get; set; }

        [ForeignKey("UserID")]
        public virtual User User { get; set; }
        public int UserID { get; set; }
    }
}
