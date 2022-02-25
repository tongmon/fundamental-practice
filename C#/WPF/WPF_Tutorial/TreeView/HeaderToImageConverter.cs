using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media.Imaging;

namespace TreeView
{
    // 전체 경로가 주어지면 특정 이미지 타입으로 변환하는 기능 수행
    [ValueConversion(typeof(string), typeof(BitmapImage))]
    public class HeaderToImageConverter : IValueConverter
    {
        public static HeaderToImageConverter Instance = new HeaderToImageConverter();

        // xaml 데이터 템플릿에 연결 시켜 주었기에 트리 노드를 활성화할 때마다 해당 함수가 작동하게 된다.
        // xaml에서 이미지의 Path를 Tag로 설정하였으니 value는 코드에서 넣어준 Tag(경로)가 된다.
        public object? Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // 전체 경로 획득
            var path = (string)value;

            if(path == null)
                return null;

            // 드라이브, 파일, 폴더에 따라 이미지를 선택해 준다.
            var name = MainWindow.GetFileFolderName(path);
            var imagePath = "/Images/file.png";

            if (string.IsNullOrEmpty(name))
                imagePath = "/Images/drive.png";
            else if(new FileInfo(path).Attributes.HasFlag(FileAttributes.Directory))
                imagePath = "/Images/folder-closed.png";

            // pack://application:,,, 이 녀석은 항상 경로 전에 붙여줘야 리소스를 잘 찾을 수 있다.
            return new BitmapImage(new Uri($"pack://application:,,,{imagePath}"));
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
