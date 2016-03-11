using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Server
{
    class Configuration
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public ulong ID { get; set; }

        [Required]
        public string Key { get; set; }

        [Required]
        public byte[] Value { get; set; }

        [ForeignKey("UserID")]
        public virtual User User { get; set; }
        public uint UserID { get; set; }
    }
}
