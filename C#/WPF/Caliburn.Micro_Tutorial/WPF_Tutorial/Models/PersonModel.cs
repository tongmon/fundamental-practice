using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Tutorial.Models
{
    public class PersonModel
    {
        public int PersonId { get; set; }
        public string? FirstName { get; set; }
        public string? LastName { get; set; }
        public int Age { get; set; }
        public DateTime DateOfBirth { get; set; }
        public bool IsAlive { get; set; }
        public decimal AccountBalance { get; set; }
        public List<AddressModel> Addresses { get; set; } = new List<AddressModel>();
        public AddressModel PrimaryAddress { get; set; }
        public string FullName
        {
            get { return FirstName + ' ' + LastName; }
        }
    }
}
