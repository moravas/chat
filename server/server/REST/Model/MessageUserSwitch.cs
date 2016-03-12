using System.ComponentModel.DataAnnotations.Schema;

namespace Server
{
    class MessageUserSwitch
    {
        [ForeignKey("ConversationID")]
        public virtual Conversation Conversation { get; set; }
        public ulong ConversationID { get; set; }

        [ForeignKey("UserID")]
        public virtual User User { get; set; }
        public uint UserID { get; set; }
    }
}
