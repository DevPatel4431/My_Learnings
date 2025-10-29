document.addEventListener("DOMContentLoaded", function () {
  const pathInput = document.getElementById("path-input");
  const addBtn = document.getElementById("add-btn");
  const pathsContainer = document.getElementById("paths-container");
  const fileTree = document.getElementById("file-tree");

  let paths = [];
  let fileStructure = { name: "Root", type: "folder", children: [], path: "" };

  // Add path when button is clicked
  addBtn.addEventListener("click", addPath);

  // Also add path when Enter is pressed
  pathInput.addEventListener("keypress", function (e) {
    if (e.key === "Enter") {
      addPath();
    }
  });

  function addPath() {
    const path = pathInput.value.trim();
    if (!path) return;

    // Add to paths list
    paths.push(path);
    updatePathsList();

    // Rebuild file structure
    buildFileStructure();

    // Render the tree
    renderFileTree();

    // Clear input
    pathInput.value = "";
    pathInput.focus();
  }

  function updatePathsList() {
    pathsContainer.innerHTML = "";
    paths.forEach((path, index) => {
      const pathItem = document.createElement("div");
      pathItem.className = "path-item";
      pathItem.innerHTML = `
                <span>${path}</span>
                <span class="delete-btn" data-index="${index}"><i class="fas fa-times"></i></span>
            `;
      pathsContainer.appendChild(pathItem);
    });

    // Add event listeners to delete buttons
    document.querySelectorAll(".delete-btn").forEach((btn) => {
      btn.addEventListener("click", function () {
        const index = parseInt(this.getAttribute("data-index"));
        paths.splice(index, 1);
        updatePathsList();
        buildFileStructure();
        renderFileTree();
      });
    });
  }

  function buildFileStructure() {
    // Reset structure
    fileStructure = { name: "Root", type: "folder", children: [], path: "" };

    // Build the structure from paths
    paths.forEach((path) => {
      const parts = path.split("/").filter((part) => part.trim() !== "");
      let currentNode = fileStructure;

      for (let i = 0; i < parts.length; i++) {
        const part = parts[i];
        const isFile = i === parts.length - 1;
        const currentPath = parts.slice(0, i + 1).join("/");

        // Check if this node already exists
        let existingNode = currentNode.children.find(
          (child) => child.name === part
        );

        if (existingNode) {
          currentNode = existingNode;
        } else {
          const newNode = {
            name: part,
            type: isFile ? "file" : "folder",
            path: currentPath,
            children: isFile ? [] : [],
          };

          currentNode.children.push(newNode);
          currentNode = newNode;
        }
      }
    });
  }

  function renderFileTree() {
    if (paths.length === 0) {
      fileTree.innerHTML =
        '<div class="empty-state">No paths added yet. Enter some paths to see the tree structure.</div>';
      return;
    }

    fileTree.innerHTML = "";
    renderNode(fileStructure, fileTree, true);

    // Add event listeners to folders
    document.querySelectorAll(".folder").forEach((folder) => {
      folder.addEventListener("click", function () {
        this.classList.toggle("expanded");
        const childrenDiv = this.nextElementSibling;
        childrenDiv.style.display =
          childrenDiv.style.display === "none" ? "block" : "none";
      });
    });
  }

  function renderNode(node, parentElement, isRoot = false) {
    const nodeElement = document.createElement("div");

    if (isRoot) {
      // Render root differently
      nodeElement.className = "folder expanded";
      nodeElement.textContent = node.name;

      const childrenDiv = document.createElement("div");
      childrenDiv.className = "children";

      node.children.forEach((child) => {
        renderNode(child, childrenDiv);
      });

      parentElement.appendChild(nodeElement);
      parentElement.appendChild(childrenDiv);
    } else if (node.type === "folder") {
      nodeElement.className = "folder";
      nodeElement.textContent = node.name;

      const childrenDiv = document.createElement("div");
      childrenDiv.className = "children";
      childrenDiv.style.display = "none";

      node.children.forEach((child) => {
        renderNode(child, childrenDiv);
      });

      parentElement.appendChild(nodeElement);
      parentElement.appendChild(childrenDiv);
    } else {
      nodeElement.className = "file";
      nodeElement.textContent = node.name;
      parentElement.appendChild(nodeElement);
    }
  }
});
