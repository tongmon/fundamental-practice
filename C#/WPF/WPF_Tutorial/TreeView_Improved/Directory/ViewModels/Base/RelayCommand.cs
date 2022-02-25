using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace TreeView_Improved
{
    // ICommand는 버튼, 트리뷰와 같은 특정 UI 실행에 필요한 로직 코드 부분을 분리하기 위해 사용된다.
    // ICommand는 CanExecuteChanged, CanExecute, Execute가 포함되는 인터페이스이다.
    // ICommand를 상속받고 위 3개의 변수 혹은 함수를 재정의하여 사용할 수 있다.
    public class RelayCommand : ICommand
    {
        private Action m_Action;

        public event EventHandler? CanExecuteChanged = (sender, e) => { };

        public RelayCommand(Action action)
        {
            m_Action = action;
        }

        public bool CanExecute(object? parameter)
        {
            return true;
        }

        public void Execute(object? parameter)
        {
            m_Action();
        }
    }
}
