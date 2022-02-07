using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
        public string FullPath { get; set; }
        public string? Name { get { return this.Type == DirectoryItemType.Drive ? this.FullPath : DirectoryStructure.GetFileFolderName(this.FullPath); } }
        // ObservableCollection 이 녀석은 list인데 list 항목이 제거되거나 추가되는 경우 PropertyChanged 처럼 알림을 줄 수가 있다.
        public ObservableCollection<DirectoryItemViewModel?>? Children { get; set; }
        public ICommand ExpandCommand { get; set; }
        public bool CanExpand { get { return this.Type != DirectoryItemType.File; } }
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
                this.Children.Add(null);
        }
        // 트리를 확장
        private void Expand()
        {

        }
    }
}
