using System.ComponentModel.DataAnnotations.Schema;

namespace Server
{
    class MessageUserSwitch
    {
        [ForeignKey("ConversationID")]
        public Conversation Conversation { get; set; }
        public ulong ConversationID { get; set; }

        [ForeignKey("UserID")]
        public User User { get; set; }
        public uint UserID { get; set; }
    }
}
