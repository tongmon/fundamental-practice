using Caliburn.Micro;
using System;
using System.Windows;
using WPF_Tutorial.ViewModels;

namespace WPF_Tutorial
{
    public class Bootstrapper : BootstrapperBase
    {
        public Bootstrapper()
        {
            Initialize();

        }

        protected override void OnStartup(object sender, StartupEventArgs e)
        {
            DisplayRootViewFor<ShellViewModel>();
        }
    }
}
