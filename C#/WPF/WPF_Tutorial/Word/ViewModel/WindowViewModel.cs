using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Word
{
    // 뷰모델
    internal class WindowViewModel : BaseViewModel
    {
        #region Private Member

        private Window mWindow;

        // 윈도우에서 내려오는 그림자의 크기
        private int mOuterMarginSize = 10;

        // 윈도우 모서리 각도
        private int mWindowRadius = 10;

        #endregion

        #region Public Properties

        // 윈도우 창 크기를 재설정하기 위한 경계선 너비
        public int ResizeBorder { get; set; } = 6;

        public Thickness ResizeBorderThickness { get { return new Thickness(ResizeBorder); } set { ResizeBorderThickness = value; } }

        // 그림자 크기 조절
        public int OuterMarginSize
        {
            get { return mWindow.WindowState == WindowState.Maximized ? 0 : mOuterMarginSize; }
            set { mOuterMarginSize = value; }
        }

        public Thickness OuterMarginSizeThickness
        {
            get { return new Thickness(OuterMarginSize); }
        }

        // 윈도우 모서리 각도
        public int WindowRadius
        {
            get
            {
                return mWindow.WindowState != WindowState.Maximized ? mOuterMarginSize : 0;
            }
            set
            {
                mWindowRadius = value;
            }
        }

        public CornerRadius WindowCornerRadius
        {
            get { return new CornerRadius(WindowRadius); }
        }

        #endregion

        #region Constructor
        public WindowViewModel(Window window)
        {
            mWindow = window;

            mWindow.StateChanged += Window_StateChanged;
        }

        private void Window_StateChanged(object? sender, EventArgs e)
        {
            
        }
        #endregion
    }
}
