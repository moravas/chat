using System.ComponentModel.DataAnnotations;

namespace Server
{
    public class Attachment
    {
        [StringLength(256, ErrorMessage = "Attachment name length exceds the maximum.")]
        public string Name { get; set; }

        public byte[] Content { get; set; }

        public uint UserID { get; set; }
    }
}
