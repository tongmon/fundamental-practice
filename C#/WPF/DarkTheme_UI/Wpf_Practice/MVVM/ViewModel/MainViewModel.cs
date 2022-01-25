using System;
using Wpf_Practice.Core;

namespace Wpf_Practice.MVVM.ViewModel
{
    class MainViewModel : ObservableObject
    {
        public HomeViewModel HomeVm { get; set; }

        private object _currentView;

        public object CurrentView
        {
            get { return _currentView; }
            set 
            { 
                _currentView = value; 
                OnPropertyChanged();
            }
        }

        public MainViewModel()
        {
            HomeVm = new HomeViewModel();
            CurrentView = HomeVm;
        }
    }
}
