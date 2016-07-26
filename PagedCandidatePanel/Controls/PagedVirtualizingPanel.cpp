#include "pch.h"
#include "PagedVirtualizingPanel.h"

using namespace PagedCandidatePanel::Controls;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;

IVectorView<float>^ PagedVirtualizingPanel::GetIrregularSnapPoints(Orientation orientation, SnapPointsAlignment alignment)
{
    auto snapPoints = ref new Platform::Collections::Vector<float>();

    if (orientation == Orientation::Horizontal)
    {
        int offset = 0;
        snapPoints->Append(offset);
        for (unsigned i = 0; i < Children->Size; ++i)
        {
            auto child = Children->GetAt(i);
            offset += child->DesiredSize.Width;
            if ((((i + 1) % 3) == 0) || (i == Children->Size - 1))
            {
                snapPoints->Append(offset);
            }
        }
    }

    return snapPoints->GetView();
}

float PagedVirtualizingPanel::GetRegularSnapPoints(Orientation orientation, SnapPointsAlignment alignment, float* offset)
{
    return 20.0f;
}

Size PagedVirtualizingPanel::MeasureOverride(Size availableSize)
{
    double width = 0;
    availableSize.Height = 44;
    for (unsigned i = 0; i < Children->Size; ++i)
    {
        auto child = Children->GetAt(i);
        child->Measure(availableSize);
        width += child->DesiredSize.Width;

        TextBlock^ tb = dynamic_cast<TextBlock^>(child);
        if (tb != nullptr)
        {
            tb->Tapped += ref new Windows::UI::Xaml::Input::TappedEventHandler(this, &PagedVirtualizingPanel::OnTapped);
        }
    }

    return Size(width, 44);
}

Size PagedVirtualizingPanel::ArrangeOverride(Size finalSize)
{
    double x = 0;
    double y = 0;

    for (unsigned i = 0; i < Children->Size; ++i)
    {
        auto child = Children->GetAt(i);

        child->Arrange(Rect(Point(x, y), child->DesiredSize));
        x += child->DesiredSize.Width;
    }

    return finalSize;
}


void PagedCandidatePanel::Controls::PagedVirtualizingPanel::OnTapped(Platform::Object ^sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs ^e)
{
    HorizontalSnapPointsChanged(this, ref new Windows::UI::Xaml::RoutedEventArgs());
}
