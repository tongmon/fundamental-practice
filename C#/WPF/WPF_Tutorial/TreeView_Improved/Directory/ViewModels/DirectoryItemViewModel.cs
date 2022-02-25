using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace TreeView_Improved
{
    // DirectoryItemViewModel는 트리의 각 노드라고 보면 된다.
    public class DirectoryItemViewModel : BaseViewModel
    {
        private ObservableCollection<DirectoryItemViewModel?>? m_Children;
        private string? m_Name;
        private DirectoryItemType m_Type;

        public DirectoryItemType Type 
        {
            get
            {
                return m_Type;
            }
            set
            {
                if (m_Type == value)
                    return;
                m_Type = value;
                Notify("Type");
            }
        }
        public string? FullPath { get; set; }
        public string? Name 
        { 
            get 
            {
                m_Name = Type == DirectoryItemType.Drive ? FullPath : DirectoryStructure.GetFileFolderName(FullPath); 
                return m_Name; 
            } 
            set 
            {
                if (m_Name == value)
                    return;
                m_Name = value;
                Notify("Name");
            }
        }
        // ObservableCollection 이 녀석은 list인데 list 항목이 제거되거나 추가되는 경우 PropertyChanged 처럼 알림을 줄 수가 있다.
        // 물론 안에 PropertyChanged를 해줘야 한다. (여기는 PropertyChanged의 Wrapper인 Notify가 사용됨.)
        public ObservableCollection<DirectoryItemViewModel?>? Children 
        {
            get
            {
                return m_Children;
            }
            set
            {
                if (m_Children == value)
                    return;
                m_Children = value;

                // Children 값이 변경이 되었다고 알려주는 역할... UI와 바인딩되어 있는 속성에 주로 사용하게 된다.
                // 이를 연결 시키는 경우에는 일반적으로 멤버 변수를 사용하여 알려주게 된다.
                Notify("Children");
            }
        }
        public ICommand ExpandCommand { get; set; }
        public DirectoryItemViewModel(string? fullPath, DirectoryItemType type)
        {
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
                // ObservableCollection에서 null이 아닌 녀석들의 수를 세어 한명이라도 있다면 true를 반환한다.
                return Children?.Count(f => f != null) > 0;
            }
            set
            {
                if (value == true)
                    Expand();
                else
                    ClearChildren();

                Notify("IsExpanded");
            }
        }

        // 폴더 내부에 볼 수 있는 폴더, 파일의 수를 반환
        private int GetSubItemCount()
        {
            var dirInfo = new System.IO.DirectoryInfo(FullPath);
            int subItemCnt = 0;
            try
            {
                var subDirList = dirInfo.GetDirectories();
                foreach (var subDir in subDirList)
                {
                    if (subItemCnt > 0) break;
                    if (!subDir.Attributes.HasFlag(FileAttributes.System) && !subDir.Attributes.HasFlag(FileAttributes.Hidden))
                        subItemCnt++;
                }
            }
            catch
            {

            }

            try
            {
                var subFileList = dirInfo.GetFiles();
                foreach (var subFile in subFileList)
                {
                    if (subItemCnt > 0) break;
                    subItemCnt++;
                }
            }
            catch
            {

            }
            return subItemCnt;
        }
        // 트리의 자식 노드를 모두 초기화
        private void ClearChildren()
        {
            Children = new ObservableCollection<DirectoryItemViewModel?>();

            if (Type != DirectoryItemType.File && GetSubItemCount() > 0)
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
