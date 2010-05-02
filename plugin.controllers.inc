<?php

/**
 * Main interface for all plugin controllers.
 */
interface PluginControllerInterface {

  /**
   * Constructor
   *
   * @param $type
   *   The plugin type this controller is managing.
   */
  public function __construct($type);

  /**
   * Load the plugin associated with the specified routing information.
   *
   * @param array $routing
   *   An associative array of values that will be used to determine which
   *   plugin is appropriate. The keys of the array are controller-dependent.
   * @return PluginInterface
   */
  public function load(array $routing = array());

  /**
   * Attach the specified plugin and config with the specified routing information.
   *
   * @param  $plugin
   *   The internal name of the plugin.
   * @param PluginConfigInterface $config
   *   The config object to use for this plugin.
   * @param array $routing
   *   An array of routing information that should retrieve this plugin and
   *   config. The keys of the array are controller-dependent.
   * @return unknown_type
   */
  public function attach($plugin, PluginConfigInterface $config, array $routing = array());

  /**
   * Detach any specified plugin from the specified routing information.
   *
   * @param array $routing
   *   The routing information from which to remove any configured plugin.
   * @return unknown_type
   */
  public function detach(array $routing);

  /**
   * Set a default plugin to use if no other plugin resolves.
   *
   * @param $plugin
   *   The internal name of the plugin.
   * @param PluginConfigInterface $config
   *   The config object to use for this plugin.
   * @return unknown_type
   */
  public function setDefault($plugin, PluginConfigInterface $config);

  /**
   * Set default properties for a plugin.
   *
   * @param $info
   *   An associative array containing the properties specified by the
   *   corresponding info hook.  This method should modify this array in-place
   *   to set any appropriate defaults for unset values.
   */
  public function setPluginDefaults(&$info);
}


/**
 * Simple controller that uses single-axis routing.
 *
 * This controller can also be used for "no routing" plugin types by just
 * not specifying any routing information. Routing information is stored
 * to the variable system for fast lookup. Note that it is not well suited
 * for controllers with highly complex config objects as those will bloat
 * the variable table.
 */
class PluginControllerVariable implements PluginControllerInterface {

  /**
   * The plugin type this controller is managing.
   *
   * @var string
   */
  protected $pluginType;

  /**
   * The info array for this plugin type.
   *
   * @var array
   */
  protected $typeInfo;

  public function __construct($type) {
    $this->pluginType = $type;
    $this->typeInfo = plugin_type_get_info($type);
  }

  public function load(array $routing = array()) {

    $routing += array('key' => 'default');
    $variable = 'plugin_' . $this->pluginType . '_' . $routing['key'];
    $plugin = variable_get($variable, NULL);
    if ($plugin) {
      list($plugin, $config) = $plugin;
      $config = unserialize($config);
      $plugin_info = plugin_get_info($this->pluginType, $plugin);
      return new $plugin_info['class']($config, $plugin_info, $routing);
    }
    else {
      $plugin = $this->typeInfo['default'];
      $plugin_info = plugin_get_info($this->pluginType, $plugin);
      $config = new $plugin_info['config'];
      return new $plugin_info['class']($config, $plugin_info, $routing);
    }
  }

  public function attach($plugin, PluginConfigInterface $config, array $routing = array()) {

  }

  public function detach(array $routing) {

  }

  public function setDefault($plugin, PluginConfigInterface $config) {

  }

  public function setPluginDefaults(&$info) {

  }

}

/**
 * Simple controller with single-axis routing that reuses controllers if available.
 *
 */
class PluginControllerVariableReuse extends PluginControllerVariable {

  /**
   * Cache of created plugins.
   *
   * @var array
   */
  protected $plugins = array();

  public function load(array $routing = array()) {
    $routing += array('key' => 'default');

    $key = $routing['key'];

    if (empty($this->plugins[$key])) {
      $this->plugins[$key] = parent::load($routing);
    }

    return $this->plugins[$key];
  }
}
