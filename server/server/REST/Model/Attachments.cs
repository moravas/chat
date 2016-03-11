using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Server
{
    class Attachments
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public uint ID { get; set; }

        [Required]
        [MaxLength(256, ErrorMessage = "Expected attachment name is too long")]
        public string Name { get; set; }

        [Required]
        public byte[] Value { get; set; }

        [ForeignKey("UserID")]
        public User User { get; set; }
        public uint UserID { get; set; }
    }
}
