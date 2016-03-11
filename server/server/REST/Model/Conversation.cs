using System;
using System.ComponentModel.DataAnnotations;

namespace Server
{
    public class Conversation
    {
        [Key]
        public uint Key { get; set; }

        public DateTime Time { get; set; }

        public string Message { get; set; }

        public uint SenderID { get; set; }
    }
}
