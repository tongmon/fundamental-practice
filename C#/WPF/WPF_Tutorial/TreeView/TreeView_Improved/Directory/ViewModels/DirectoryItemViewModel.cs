using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace TreeView_Improved
{
    // DirectoryItemViewModel는 트리의 각 노드라고 보면 된다.
    public class DirectoryItemViewModel : BaseViewModel
    {
        public DirectoryItemType Type { get; set; }
        public string? FullPath { get; set; }
        public string? Name 
        { 
            get { return Type == DirectoryItemType.Drive ? FullPath : DirectoryStructure.GetFileFolderName(FullPath); } 
            set { Name = value; Notify("Name"); }
        }
        // ObservableCollection 이 녀석은 list인데 list 항목이 제거되거나 추가되는 경우 PropertyChanged 처럼 알림을 줄 수가 있다.
        public ObservableCollection<DirectoryItemViewModel?>? Children { get; set; }
        public ICommand ExpandCommand { get; set; }
        public DirectoryItemViewModel(string? fullPath, DirectoryItemType type)
        {
            //PropertyChanged += DirectoryItemViewModel_PropertyChanged;

            ExpandCommand = new RelayCommand(Expand); // 트리 노드 확장시에 발동되는 함수를 붙여준다.

            FullPath = fullPath;
            Type = type;

            ClearChildren();
        }

        private void DirectoryItemViewModel_PropertyChanged(object? sender, PropertyChangedEventArgs e)
        {
            switch (e.PropertyName)
            {
                case "Name":

                    break;

                case "Children":

                    break;
            }
        }

        public bool CanExpand { get { return Type != DirectoryItemType.File; } }
        // TreeView의 트리 확장, 축소 이벤트와 연결되어 있는 함수이다. (연결은 xaml에서 지정한다.)
        public bool IsExpanded
        {
            get
            {
                // ObservableCollection에서 null이 아닌 녀석들이 있다면 true를 반환한다.
                return Children?.Count(f => f != null) > 0;
            }
            set
            {
                if (value == true)
                    Expand();
                else
                    ClearChildren();
            }
        }
        // 트리의 자식 노드를 모두 초기화
        private void ClearChildren()
        {
            Children = new ObservableCollection<DirectoryItemViewModel?>();
            if(Type != DirectoryItemType.File)
                Children.Add(null);
        }
        // 트리를 확장
        private void Expand()
        {
            // 파일인 경우 트리 노드 확장 불가
            if (DirectoryItemType.File == Type)
                return;
            // DirectoryStructure.GetDirectoryContents(FullPath) 이 부분에서 DirectoryItem형의 List를 반환하고
            // 해당 자료형은 Select 함수에 의해서 화면에 보이는 이벤트와 연관된 트리 노드 자료형인 DirectoryItemViewModel형 List로 변환된다.
            Children = new ObservableCollection<DirectoryItemViewModel?>(
                DirectoryStructure.GetDirectoryContents(FullPath).Select(content => new DirectoryItemViewModel(content.FullPath, content.Type)));
        }
    }
}
