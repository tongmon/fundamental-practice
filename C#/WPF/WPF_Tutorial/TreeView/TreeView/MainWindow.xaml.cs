using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TreeView
{
    /// <summary>
    /// 모든 로직은 여기에 담기게 된다... MVVM 패턴에 비하면 코드 작업이 진행될 수록 복잡해진다.
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Constructor
        public MainWindow()
        {
            InitializeComponent();

        }
        #endregion

        // 윈도우가 화면에 보여지기 전에 수행될 행위들...
        #region On Loaded
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            // Directory.GetLogicalDrives()는 컴퓨터에 달려있는 드라이브에 대한 정보가 들어간다.
            // 예를 들어 C드라이브, D드라이브 등...
            foreach (var drive in Directory.GetLogicalDrives())
            {
                var item = new TreeViewItem() 
                {
                    // 헤더 설정
                    Header = drive,
                    // 전체 경로 설정
                    Tag = drive
                };

                // item 하위에 아이템을 추가하여 트리뷰 노드 확장을 활성화한다.
                item.Items.Add(null);

                // 트리뷰 노드가 확장되는 순간 발생되는 이벤트 핸들러를 추가한다.
                item.Expanded += Folder_Expanded;

                // xaml에서 선언된 TreeView 아이템인 FolderView에 item을 추가한다.
                FolderView.Items.Add(item);
            }
        }
        #endregion

        // 트리뷰 노드가 확장되는 순간 발생되는 이벤트 핸들러 함수
        private void Folder_Expanded(object sender, RoutedEventArgs e)
        {
            #region Initial Checks

            var item = (TreeViewItem)sender;

            // 아이템이 먼가를 들고 있는 경우는 그냥 return 한다.
            if (item.Items.Count != 1 || item.Items[0] != null)
                return;

            // 아이템이 더미 데이터를 들고 있는 경우는 더미 데이터를 지운다.
            item.Items.Clear();

            // 폴더 이름 획득
            var fullPath = (string)item.Tag;

            #endregion

            #region Get Folders

            var dirList = new List<string>();

            try
            {
                var dirs = Directory.GetDirectories(fullPath);
            
                // 하위 아이템 추가를 위한 for문
                dirList.AddRange(dirs);
            }
            catch
            {

            }

            foreach (var directory in dirList)
            {
                // 시스템, 숨김 속성을 가지는 디렉터리들은 생략한다.
                var dirInfo = new System.IO.DirectoryInfo(directory);
                if(dirInfo.Attributes.HasFlag(FileAttributes.System) && dirInfo.Attributes.HasFlag(FileAttributes.Hidden))
                    continue;

                // 디렉터리 아이템 생성
                var subItem = new TreeViewItem()
                {
                    Header = GetFileFolderName(directory),
                    Tag = directory
                };

                // 폴더 내의 파일이나 다른 폴더가 없다면 확장을 지원할 필요가 없다.
                var subItemCnt = 0;
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

                // 노드 확장을 위한 더미 아이템 추가
                if (subItemCnt > 0)
                    subItem.Items.Add(null);

                subItem.Expanded += Folder_Expanded;

                // 해당 아이템을 부모 아이템에 추가한다.
                item.Items.Add(subItem);
            }

            #endregion

            #region Get Files

            var fileList = new List<string>();
            try
            {
                var files = Directory.GetFiles(fullPath);

                // 하위 아이템 추가를 위한 for문
                fileList.AddRange(files);
            }
            catch 
            {
            
            }

            foreach (var file in fileList)
            {
                // 디렉터리 아이템 생성
                var subItem = new TreeViewItem()
                {
                    Header = GetFileFolderName(file),
                    Tag = file
                };

                // 해당 아이템을 부모 아이템에 추가한다.
                item.Items.Add(subItem);
            }

            #endregion
        }

        // 주어진 경로에서 파일이나 폴더 이름을 찾음
        public static string? GetFileFolderName(string path)
        {
            // 주어진 경로가 없으면 null 반환
            if(string.IsNullOrEmpty(path))
                return null;

            // 경로 정규화
            var normalizePath = path.Replace('/', '\\');

            // 마지막 \ 녀석의 인덱스 찾기
            var lastIndex = normalizePath.LastIndexOf('\\');

            // \를 찾지 못했으면 주어진 경로 반환
            if (lastIndex <= 0)
                return path;

            // 파일 이름을 획득
            return path.Substring(lastIndex + 1);
        }
    }
}
