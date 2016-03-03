using System;
using System.ComponentModel.DataAnnotations;

namespace Server
{
    public class MessageUserSwitch
    {
        [Key]
        public ulong MessageID { get; set; }

        public uint UserID { get; set; }
    }
}
