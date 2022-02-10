using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TreeView_Improved
{
    // INotifyPropertyChanged 이 녀석은 바인딩된 인터페이스 요소의 녀석 값이 코드에서 바뀌거나 UI적으로 바뀌면
    // 호출되는 이벤트를 정의할 수 있게 한다.
    public class BaseViewModel : INotifyPropertyChanged
    {
        // PropertyChanged는 이벤트 핸들러다.
        // 함수 포인터를 여러개 붙일 수 있다.
        // 사용법은 다음과 같은데 어떤 함수 property_test가 있다고 하자.
        // 특정 바인딩된 변수가 변할 때 마다 property_test가 실행되게 하고 싶다면
        // PropertyChanged += property_test;로 이벤트 함수를 추가해준 뒤에 특정 바인딩된 변수의 set에
        // PropertyChanged(this, new PropertyChangedEventArgs(특정 바인딩된 변수 이름));를 호출해주면 된다.
        // 무슨 말인지 모르겠다면 코드를 보면서 이해하면 쉽다.
        public event PropertyChangedEventHandler? PropertyChanged;

        protected void Notify(string propName)
        {
            if (this.PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }
    }
}
