using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Server
{
    class Configurations
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public ulong ID { get; set; }

        [Required]
        public string Key { get; set; }

        [Required]
        public byte[] Value { get; set; }

        [ForeignKey("UserID")]
        public User User { get; set; }
        public uint UserID { get; set; }
    }
}
