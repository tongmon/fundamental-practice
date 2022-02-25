using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;

namespace TreeView_Improved
{
    public class DirectoryStructureViewModel : BaseViewModel
    {
        private ObservableCollection<DirectoryItemViewModel> m_Items;

        // 장치에 존재하는 모든 드라이브 정보 리스트
        // UI와 바인딩되어 있다.
        public ObservableCollection<DirectoryItemViewModel> Items 
        {
            get
            {
                return m_Items;
            }

            set
            {
                if(m_Items == value)
                    return;
                m_Items = value;
                Notify("Items");
            }
        }

        public DirectoryStructureViewModel()
        {
            Items = new ObservableCollection<DirectoryItemViewModel>(
                DirectoryStructure.GetLogicalDrives().Select(drive => new DirectoryItemViewModel(drive.FullPath, drive.Type)));
        }
    }
}
