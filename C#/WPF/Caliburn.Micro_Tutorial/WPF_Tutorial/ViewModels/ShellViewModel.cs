using Caliburn.Micro;
using System;
using System.Diagnostics;
using WPF_Tutorial.Models;

// 실제 인터페이스에 관한 로직이 들어가는 부분.
// 데이터를 다루긴 하지만 실제 사용자가 보는 것에 대한 데이터를 보통 다룬다.

namespace WPF_Tutorial.ViewModels
{
    public class ShellViewModel : Conductor<object>
    {
        private string _firstName = "Tim";
        private string _lastName;
        private BindableCollection<PersonModel> _people = new BindableCollection<PersonModel>(); // PersonModel 클래스를 바인딩 가능한 변수로 선언
        private PersonModel _selectedPerson;

        public ShellViewModel()
        {
            People.Add(new PersonModel { FirstName = "Tim", LastName = "Corey" });
            People.Add(new PersonModel { FirstName = "Bill", LastName = "Jones" });
            People.Add(new PersonModel { FirstName = "Sue", LastName = "Storm" });
        }

        public string FirstName
        {
            get { return _firstName; }
            set
            {
                _firstName = value;
                NotifyOfPropertyChange(() => FirstName); // FirstName 얘가 변할 때 화면에 보여지는 FirstName과 바인딩된 컨트롤이 변함
            }
        }
        public string LastName
        {
            get { return _lastName; }
            set
            {
                _lastName = value;
                NotifyOfPropertyChange(() => LastName); // LastName 얘가 변할 때 화면에 보여지는 LastName과 바인딩된 컨트롤이 변함
                NotifyOfPropertyChange(() => FullName); // LastName 얘가 변할 때 화면에 보여지는 FullName과 바인딩된 컨트롤이 변함
            }
        }
        public string FullName
        {
            get { return FirstName + " " + LastName; }
        }

        public BindableCollection<PersonModel> People
        {
            get { return _people; }
            set { _people = value; }
        }      
        public PersonModel SelectedPerson
        {
            get { return _selectedPerson; }
            set
            {
                _selectedPerson = value;
                NotifyOfPropertyChange(() => SelectedPerson);
            }
        }
        public bool CanClearText(string firstName, string lastName)
        {
            return !String.IsNullOrWhiteSpace(firstName) || !String.IsNullOrWhiteSpace(lastName);
        }
        public void ClearText(string firstName, string lastName)
        {
            FirstName = "";
            LastName = "";
        }
        public void LoadPageOne()
        {
            ActivateItemAsync(new FirstChildViewModel());
        }

        public void LoadPageTwo()
        {
            ActivateItemAsync(new SecondChildViewModel());
        }
    }
}
