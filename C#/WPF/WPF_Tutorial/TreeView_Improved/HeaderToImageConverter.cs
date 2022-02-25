using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media.Imaging;

namespace TreeView_Improved
{
    // 전체 경로가 주어지면 특정 이미지 타입으로 변환하는 기능 수행
    [ValueConversion(typeof(string), typeof(BitmapImage))]
    public class HeaderToImageConverter : IValueConverter
    {
        public static HeaderToImageConverter Instance = new HeaderToImageConverter();

        // xaml 데이터 템플릿에 연결 시켜 주었기에 트리 노드를 활성화할 때마다 해당 함수가 작동하게 된다.
        // value는 xaml에서 설정한대로 DirectoryItem의 Type이 된다.
        public object? Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {

            // 드라이브, 파일, 폴더에 따라 이미지를 선택해 준다.
            var imagePath = "/Images/file.png";

            switch ((DirectoryItemType)value)
            {
                case DirectoryItemType.Drive:
                    imagePath = "/Images/drive.png";
                    break;
                case DirectoryItemType.Folder:
                    imagePath = "/Images/folder-closed.png";
                    break;
            }

            // pack://application:,,, 이 녀석은 항상 경로 전에 붙여줘야 리소스를 잘 찾을 수 있다.
            return new BitmapImage(new Uri($"pack://application:,,,{imagePath}"));
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
