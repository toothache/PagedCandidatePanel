#pragma once
namespace PagedCandidatePanel
{
    namespace Controls
    {
        public ref class PagedVirtualizingPanel sealed:
            public Windows::UI::Xaml::Controls::Panel,
            public Windows::UI::Xaml::Controls::Primitives::IScrollSnapPointsInfo
        {
        //internal:
        //    PagedVirtualizingPanel();
        public:
            //interface IScrollSnapPointsInfo
            virtual event Windows::Foundation::EventHandler<Object^>^ HorizontalSnapPointsChanged;
            virtual event Windows::Foundation::EventHandler<Object^>^ VerticalSnapPointsChanged;

            virtual Windows::Foundation::Collections::IVectorView<float>^ GetIrregularSnapPoints(
                _In_ Windows::UI::Xaml::Controls::Orientation orientation,
                _In_ Windows::UI::Xaml::Controls::Primitives::SnapPointsAlignment alignment) override;

            virtual float GetRegularSnapPoints(
                _In_ Windows::UI::Xaml::Controls::Orientation orientation,
                _In_ Windows::UI::Xaml::Controls::Primitives::SnapPointsAlignment alignment,
                _Out_ float* offset) override;

            property bool AreHorizontalSnapPointsRegular
            {
                virtual bool get() override { return false; }
            }

            property bool AreVerticalSnapPointsRegular
            {
                virtual bool get() override { return true; }
            }

        protected:
            virtual Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size availableSize) override;
            virtual Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size finalSize) override;
            void OnTapped(Platform::Object ^sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs ^e);
        };

    }
}