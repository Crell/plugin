<?php

/**
 * Main interface for all Plugins.
 */
interface PluginInterface {

  /**
   * Constructor
   *
   * @param $context
   *   The context object bound to this controller and routing information.
   * @param $definition
   *   The definition array used to declare this plugin.  This is useful
   *   when several plugins share a single class implementation.
   * @param array $routing
   *   The routing information that was used to load this controller. Some
   *   controllers may make use of that information.
   */
  public function __construct($context, array $definition, array $routing = array());

}

/**
 * A base implementation of a plugin object.
 */
class PluginBaseAbstract implements PluginInterface {

  /**
   * The context object for this plugin.
   *
   * @var PluginContextInterface
   */
  protected $context;

  /**
   * The routing information used to retrieve this object.
   *
   * @var array
   */
  protected $routing = array();

  /**
   * The definition information for this controller.
   *
   * @var array
   */
  protected $definition = array();

  public function __construct($context, array $definition, array $routing = array()) {
    $this->context = $context;
    $this->definition = $definition;
    $this->routing = $routing;
  }

}
