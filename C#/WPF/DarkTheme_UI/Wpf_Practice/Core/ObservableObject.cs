using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace Wpf_Practice.Core
{
    // INotifyPropertyChanged -> 원본 속성 또는 대상 속성이 변경되면 다른 항목이 자동으로 업데이트 되도록 하고 싶을 때 사용
    internal class ObservableObject : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler? PropertyChanged;

        // OnPropertyChanged -> name에 해당하는 이름을 갖는 데이터에 변화가 생길때마다 이벤트를 발생시키는 메서드
        protected void OnPropertyChanged([CallerMemberName] string? name = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
