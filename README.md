# CreateWinAPI32BalloonNotification - README

## Overview

The `CreateWinAPI32BallonNotification` function is a C++ utility designed to generate a Windows system tray notification using the Win32 API. This function allows you to create a balloon-style notification with a title, message, and customizable icon. The notification can be configured to represent various types of alerts, such as informational messages, errors, warnings, or simple notifications without an icon.

## Function Prototype

```cpp
void CreateWinAPI32BallonNotification(std::string _title, std::string _message, int _type = 0);
```

## Parameters

- **_title**: A `std::string` that represents the title of the notification. This will be prominently displayed at the top of the notification balloon.

- **_message**: A `std::string` that contains the message body of the notification. This text will appear below the title in the balloon.

- **_type**: An integer that specifies the type of notification. The value of this parameter determines the icon and style of the notification:
  - **0**: Information notification (default). Displays an information icon.
  - **1**: Error notification. Displays an error icon.
  - **2**: Warning notification. Displays a warning icon.
  - **3**: No icon notification. No icon is displayed.

  **Note**: If an invalid type is provided, the function will print an error message and terminate the program by calling `exit(1)`.

## Detailed Description

### Purpose

The `CreateWinAPI32BallonNotification` function leverages the Windows API to provide a simple interface for displaying system tray notifications. These notifications can be useful in various applications to inform users of important events, errors, or updates without requiring them to switch away from their current task.

### Internal Mechanics

1. **Loading Module Handle**: The function begins by retrieving the current module's handle using `GetModuleHandle(NULL)`. This handle is necessary for loading resources such as icons.

2. **Setting Up NOTIFYICONDATAW Structure**:
    - The `NOTIFYICONDATAW` structure is a key component in creating a notification. It contains all the necessary information, such as the window handle, notification ID, icon, tooltip, and message.
    - The structure is zero-initialized and then populated based on the parameters provided to the function.

3. **Configuring Notification Type**:
    - The `_type` parameter determines the notification's icon and behavior. The function uses a `switch` statement to assign appropriate flags to the `NOTIFYICONDATAW` structure.
    - Each notification type is associated with a unique `uID`, `uFlags`, and `dwInfoFlags`.

4. **Loading Icon**:
    - The `LoadIcon` function is used to load the default information icon (`IDI_INFORMATION`). For other icons, such as error or warning, the structure’s `dwInfoFlags` field is set to correspond to the desired icon type.

5. **String Conversion**:
    - The title and message strings provided by the user are converted from `std::string` to `std::wstring` using a utility function `Utils::StringToWString`. This is necessary because the Win32 API expects wide-character strings (`wchar_t*`) in the `NOTIFYICONDATAW` structure.

6. **Setting Tooltip and Message Text**:
    - The tooltip, title, and message fields of the notification are populated using `StringCchCopyW`, a safe string copy function that prevents buffer overflows. The tooltip is hardcoded to "My App Notification," while the title and message are set based on user input.

7. **Display Duration**:
    - The notification is set to display for 2000 milliseconds (2 seconds) using the `uTimeout` field of the `NOTIFYICONDATAW` structure.

8. **Displaying the Notification**:
    - The `Shell_NotifyIconW` function is called twice. The first call (`NIM_ADD`) adds the notification to the system tray, and the second call (`NIM_MODIFY`) updates the notification with the provided details.

### Notes

- **Window Handle (`hWnd`)**: The function uses `NULL` for the window handle (`hWnd`), meaning it does not associate the notification with any specific window. If you need the notification to interact with a specific window, this should be adjusted accordingly.

- **Error Handling**: If an invalid notification type is provided, the function prints an error message and calls `exit(1)` to terminate the program. This behavior can be modified if necessary.

- **Unicode Compatibility**: The function exclusively uses the Unicode version of the `Shell_NotifyIcon` function (`Shell_NotifyIconW`). Ensure your project is configured to support Unicode if necessary.

## Example Usage

```cpp
#include <iostream>
#include <string>

// Assuming Utils::StringToWString is defined somewhere
namespace Utils {
    std::wstring StringToWString(const std::string& str);
}

int main() {
    CreateWinAPI32BallonNotification("Update Available", "A new update has been installed successfully.", 0);
    return 0;
}
```

### Explanation

In this example, a simple informational notification is created with the title "Update Available" and the message "A new update has been installed successfully." The notification is displayed in the system tray for 2 seconds with an information icon.

## Considerations

- **Customization**: The function can be expanded to include more features, such as custom icons, longer display times, or actions upon clicking the notification.
- **Resource Management**: Depending on the application's needs, consider managing the icon resource more carefully (e.g., unloading it when no longer needed).
- **Cross-Version Compatibility**: Ensure that the target Windows version supports the `Shell_NotifyIconW` function. Most modern Windows versions do, but it's good practice to verify.

## Conclusion

The `CreateWinAPI32BallonNotification` function provides a straightforward way to create customizable system tray notifications in a Windows environment. It abstracts much of the complexity of working with the Win32 API while offering flexibility through its parameters. Whether for alerting users to important updates or signaling errors, this function is a valuable tool in any Windows-based C++ application.
